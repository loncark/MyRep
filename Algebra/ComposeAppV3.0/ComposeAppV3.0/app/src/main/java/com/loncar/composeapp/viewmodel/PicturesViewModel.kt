package com.loncar.composeapp.viewmodel

import android.net.Uri
import android.util.Log
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.google.firebase.storage.FirebaseStorage
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.repository.PicturesRepository
import com.loncar.composeapp.view.common.toAbsPath
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.launch
import javax.inject.Inject
import kotlin.properties.Delegates
import kotlin.random.Random

@HiltViewModel
class PicturesViewModel @Inject constructor(
    private val picturesRepository: PicturesRepository,
    private val _picturesState: MutableState<PicturesState>
) : ViewModel() {
    val picturesState: State<PicturesState> get() = _picturesState      // turns the state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("PICTURES_VIEWMODEL", e.toString(), e)
    }

    fun createAndUploadNewPicture(
        uploadState: UploadState,
        currentUserHandle: String,
    ) {
        // 1. upload the pic to storage and retrieve download url
        var newUri = ""
        storageUpload(uploadState.uri!!, currentUserHandle) { downloadUrl ->
            newUri = downloadUrl.toString()

            // 2. create the new Picture
            val id = picturesState.value.pictures.size + 1
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

            // 3. upload the Picture to json database
            val databaseReference = FirebaseDatabase.getInstance().getReference("pictures/picture${newPicture.id}")
            databaseReference.addValueEventListener(object : ValueEventListener {
                override fun onDataChange(snapshot: DataSnapshot) {
                    // inside the method of on Data change we are setting
                    // our object class to our database reference.
                    // data base reference will sends data to firebase.
                    databaseReference.setValue(newPicture)
                    println("JSON PICTURES SUCCESSFULLY UPDATED")

                    // 4. reload the pictureVM
                    reload()
                }
                override fun onCancelled(error: DatabaseError) {
                    println("FAILED TO UPDATE PICTURES JSON: $error")
                }

            })
        }
    }

    private fun storageUpload(uri: Uri, currentUserHandle: String, callback: (Uri) -> Unit) {
        val storage = FirebaseStorage.getInstance()

        storage.reference.child("pictures/${currentUserHandle}/${uri.lastPathSegment}").putFile(uri).addOnCompleteListener { task ->
            if (task.isSuccessful) {    // THIS DOES THE UPLOAD!
                storage.reference.child(task.result!!.metadata!!.path).downloadUrl.addOnSuccessListener { uri ->
                    callback(uri)
                }
            } else {
                println("STORAGE UPLOAD FAILED")
            }
        }
    }

    private fun reload() {
        viewModelScope.launch(errorHandler) {
            val allPictures = picturesRepository.getPictures()

            allPictures.forEach {
                it.resource = toAbsPath(it.resource)
            }

            _picturesState.value = _picturesState.value.copy(
                pictures = allPictures,
                loading = false
            )
        }
    }

    init { reload() }
}
