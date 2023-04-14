package com.loncar.composeapp.viewmodel

import android.content.Context
import android.graphics.*
import android.net.Uri
import android.util.Log
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.storage.FirebaseStorage
import com.loncar.composeapp.di.MainDispatcher
import com.loncar.composeapp.logger.*
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.repository.PicturesRepository
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.launch
import retrofit2.HttpException
import java.io.ByteArrayOutputStream
import java.net.ConnectException
import java.net.UnknownHostException
import javax.inject.Inject
import kotlin.random.Random

@HiltViewModel
class PicturesViewModel @Inject constructor(
    private val picturesRepository: PicturesRepository,
    private val _picturesState: MutableState<PicturesState>,
    @MainDispatcher private val dispatcher: CoroutineDispatcher     // necessary for process testing
) : ViewModel() {
    val picturesState: State<PicturesState> get() = _picturesState      // turns the state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("PICTURES_VIEWMODEL", e.toString(), e)
    }

    fun createAndUploadNewPictureToFirebase(
        uploadState: UploadState,
        currentUserHandle: String,
        context : Context,
        noConnectionToast: () -> Unit,
        uploadSuccessfulToast: () -> Unit,
        noPictureSelectedToast: () -> Unit
    ) {
        // 1. upload the pic to storage and retrieve download url
        if (uploadState.uri == null) {
            noPictureSelectedToast()
            return
        }

        if(uploadState.filter != Filter.NONE) {
            applyFilterAndUploadToStorage(uploadState.filter, context, uploadState.uri, currentUserHandle) { downloadUrl ->
                realtimeDbUpload(
                    downloadUrl,
                    currentUserHandle,
                    uploadState,
                    uploadSuccessfulToast,
                    noConnectionToast
                )
            }
        }
        else {
            uploadToStorage(uploadState.uri, currentUserHandle) { downloadUrl ->
                realtimeDbUpload(
                    downloadUrl,
                    currentUserHandle,
                    uploadState,
                    uploadSuccessfulToast,
                    noConnectionToast
                )
            }
        }
    }

    private fun applyFilterAndUploadToStorage(filter: Filter, context: Context, uri: Uri, currentUserHandle: String, callback: (Uri) -> Unit) {
        val storage = FirebaseStorage.getInstance()
        val data: ByteArray = when (filter) {
            Filter.GRAYSCALE -> applyGreyscaleFilter(context, uri)
            Filter.SEPIA -> applySepiaFilter(context, uri)
            else -> ByteArray(0)
        }

        storage.reference.child("pictures/${currentUserHandle}/${uri.lastPathSegment}").putBytes(data)
            .addOnCompleteListener { task ->
                if (task.isSuccessful) {
                    println("Storage upload successful.")
                    storage.reference.child(task.result!!.metadata!!.path).downloadUrl.addOnSuccessListener { uri ->
                        callback(uri)
                    }
                } else {
                    println("STORAGE UPLOAD FAILED")
                }
            }
    }

    private fun applyGreyscaleFilter(context: Context, uri: Uri): ByteArray {
        // Load the bitmap from the Uri
        val inputStream = context.contentResolver.openInputStream(uri)
        val bitmap = BitmapFactory.decodeStream(inputStream)

        // Apply the grayscale filter to the bitmap
        val grayBitmap = Bitmap.createBitmap(bitmap.width, bitmap.height, Bitmap.Config.ARGB_8888)
        val canvas = Canvas(grayBitmap)
        val paint = Paint()
        val colorMatrix = ColorMatrix()
        colorMatrix.setSaturation(0f)
        val filter = ColorMatrixColorFilter(colorMatrix)
        paint.colorFilter = filter
        canvas.drawBitmap(bitmap, 0f, 0f, paint)

        // Upload the grayscale image to Firebase Storage
        val baos = ByteArrayOutputStream()
        grayBitmap.compress(Bitmap.CompressFormat.JPEG, 100, baos)
        return baos.toByteArray()
    }

    private fun applySepiaFilter(context: Context, uri: Uri): ByteArray {
        // Load the bitmap from the Uri
        val inputStream = context.contentResolver.openInputStream(uri)
        val bitmap = BitmapFactory.decodeStream(inputStream)

        // Apply the sepia filter to the bitmap
        val sepiaMatrix = ColorMatrix(sepiaMatrix)
        val sepiaPaint = Paint()
        sepiaPaint.colorFilter = ColorMatrixColorFilter(sepiaMatrix)

        val sepiaBitmap = Bitmap.createBitmap(bitmap.width, bitmap.height, Bitmap.Config.ARGB_8888)
        val canvas = Canvas(sepiaBitmap)
        canvas.drawBitmap(bitmap, 0f, 0f, sepiaPaint)

        // Upload the sepia image to Firebase Storage
        val baos = ByteArrayOutputStream()
        sepiaBitmap.compress(Bitmap.CompressFormat.JPEG, 100, baos)
        return baos.toByteArray()
    }

    private fun realtimeDbUpload(
        downloadUrl: Uri,
        currentUserHandle: String,
        uploadState: UploadState,
        uploadSuccessfulToast: () -> Unit,
        noConnectionToast: () -> Unit
    ) {
        val newUri = downloadUrl.toString()

        // 2. create the new Picture
        val newPicture = newPicture(currentUserHandle, uploadState, newUri)

        // 3. upload the Picture to json database
        try {
            val databaseReference = FirebaseDatabase.getInstance()
                .getReference("pictures/picture${newPicture.id}")
            databaseReference.setValue(newPicture).addOnSuccessListener {
                println("JSON pictures successfully updated.")
                uploadSuccessfulToast()

                // 4. reload the pictureVM
                reload()
                PictureUploadLogger().templatePrint(newPicture.handle, newPicture.id)
            }.addOnFailureListener { error ->
                println("FAILED TO UPDATE PICTURES JSON: $error")
            }
        } catch (e: Exception) {
            when (e) {      // will actually never happen because the update will happen as soon as the internet is turned on
                is UnknownHostException,
                is ConnectException,
                is HttpException -> {
                    noConnectionToast()
                }
                else -> noConnectionToast()
            }
        }
    }

    private fun newPicture(
        currentUserHandle: String,
        uploadState: UploadState,
        newUri: String
    ): Picture {

        var id = picturesState.value.pictures.size
        picturesState.value.pictures.forEach {
            if (it.id.toInt() > id) {
                id = it.id.toInt()
            }
        }
        id += 1
        val thisLat = Random.nextDouble(from = 45.75, until = 45.85)
        val thisLng = Random.nextDouble(from = 15.85, until = 16.1)

        val newPicture = Picture(
            id = "$id",
            handle = currentUserHandle,
            description = uploadState.description,
            resource = newUri,
            lat = thisLat.toString(),
            lng = thisLng.toString(),
            hashtags = uploadState.hashtags
        )
        println("NEW PICTURE: $newPicture")
        return newPicture
    }

    private fun uploadToStorage(uri: Uri, currentUserHandle: String, callback: (Uri) -> Unit) {
        val storage = FirebaseStorage.getInstance()

        storage.reference.child("pictures/${currentUserHandle}/${uri.lastPathSegment}").putFile(uri)
            .addOnCompleteListener { task ->
                if (task.isSuccessful) {
                    println("Storage upload successful.")
                    storage.reference.child(task.result!!.metadata!!.path).downloadUrl.addOnSuccessListener { uri ->
                        callback(uri)
                    }
                } else {
                    println("STORAGE UPLOAD FAILED")
                }
            }
    }

    fun deletePictureFromFirebase(
        id: Int,
        url: String,
        currentUserHandle: String,
        deleteSuccessful: () -> Unit,
        noConnectionToast: () -> Unit
    ) {
        try {
            val storageRef = FirebaseStorage.getInstance().getReferenceFromUrl(url)
            storageRef.delete().addOnSuccessListener {
                println("Picture$id storage delete successful.")

                val databaseReference = FirebaseDatabase.getInstance().getReference("pictures/picture$id")
                databaseReference.removeValue().addOnSuccessListener {
                    println("Picture$id deleted successfully.")
                    deleteSuccessful()

                    reload()
                    PictureDeleteLogger().templatePrint(currentUserHandle, id.toString())
                }.addOnFailureListener { error ->
                    println("FAILED TO DELETE PICTURE: $error")
                }
            }.addOnFailureListener {
                println("STORAGE DELETE FAILED")
            }
        } catch (e: Exception) {
            when (e) {
                is UnknownHostException,
                is ConnectException,
                is HttpException -> {
                    println("No internet connection.")
                    noConnectionToast()
                }
                else -> {
                    println(e.toString())
                }
            }
        }
    }

    fun updatePicture(
        uploadState: UploadState,
        currentUserHandle: String,
        noConnectionToast: () -> Unit,
        updateSuccessfulToast: () -> Unit
    ) {
        val id = uploadState.pictureToUpdateId
        val thisPicture = picturesState.value.pictures.find { it.id == id.toString() }
        thisPicture!!.description = uploadState.description
        thisPicture.hashtags = uploadState.hashtags

        try {
            val databaseReference = FirebaseDatabase.getInstance().getReference("pictures/picture$id")
            databaseReference.setValue(thisPicture).addOnSuccessListener {
                println("JSON pictures successfully updated.")
                updateSuccessfulToast()

                reload()
                PictureUpdateLogger().templatePrint(currentUserHandle, id.toString())
            }.addOnFailureListener { error ->
                println("FAILED TO UPDATE PICTURES JSON: $error")
            }
        } catch (e: Exception) {
            when (e) {
                is UnknownHostException,
                is ConnectException,
                is HttpException -> {
                    noConnectionToast()
                }
                else -> throw e
            }
        }
    }

    private fun reload() {
        viewModelScope.launch(errorHandler + dispatcher) {
            _picturesState.value = _picturesState.value.copy(
                loading = true
            )

            val allPictures = picturesRepository.getPicturesAndUpdateLocalDatabase()

            _picturesState.value = _picturesState.value.copy(
                pictures = allPictures,
                loading = false
            )
        }
    }

    init {
        reload()
    }
}
