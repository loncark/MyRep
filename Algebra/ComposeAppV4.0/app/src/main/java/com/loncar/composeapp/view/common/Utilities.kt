package com.loncar.composeapp.view.common

import android.content.Context
import android.graphics.Bitmap
import android.location.Geocoder
import android.os.Environment
import android.util.Log
import androidx.core.content.ContextCompat
import com.google.android.gms.maps.model.BitmapDescriptor
import com.google.android.gms.maps.model.BitmapDescriptorFactory
import com.google.firebase.storage.FirebaseStorage
import com.loncar.composeapp.model.Picture
import kotlinx.coroutines.tasks.await
import java.io.File
import java.util.*
import java.util.regex.Pattern

fun String.isValidPassword() =
    Pattern.compile(
        "^" +
                "(?=.*[0-9])" +         //at least 1 digit
                "(?=.*[a-z])" +         //at least 1 lower case letter
                "(?=.*[A-Z])" +         //at least 1 upper case letter
                "(?=.*[a-zA-Z])" +      //any letter
                "(?=.*[@#$%^&+=])" +    //at least 1 special character
                "(?=\\S+$)" +           //no white spaces
                ".{8,}" +               //at least 8 characters
                "$"
    ).matcher(this).matches()

fun bitmapDescriptorFromVector(
    context: Context,
    vectorResId: Int
): BitmapDescriptor? {

    // retrieve the actual drawable
    val drawable = ContextCompat.getDrawable(context, vectorResId) ?: return null
    drawable.setBounds(0, 0, drawable.intrinsicWidth, drawable.intrinsicHeight)
    val bm = Bitmap.createBitmap(
        drawable.intrinsicWidth,
        drawable.intrinsicHeight,
        Bitmap.Config.ARGB_8888
    )

    // draw it onto the bitmap
    val canvas = android.graphics.Canvas(bm)
    drawable.draw(canvas)
    return BitmapDescriptorFactory.fromBitmap(bm)
}

// this one breaks the code for some dumb reason so I rewrote picturesSetup.py with https addresses
// converts gs:// paths of google storage to https:// paths accessible to AsyncImage
suspend fun toAbsPath(relPath: String): String {
    if(relPath[0] != 'g') { return relPath }

    //FirebaseApp.initializeApp(context) is in MainActivity
    val storage = FirebaseStorage.getInstance()

    val imageRef = storage.getReferenceFromUrl(relPath)
    return imageRef.downloadUrl.addOnSuccessListener {
        it.toString()
    }.addOnFailureListener {
        ""
        println("TOABSPATH() FAILED")
    }.await().toString()
}

// image is found at: Files -> Internal Storage -> Android -> data -> com...composeapp -> Files
fun downloadImage(path: String, context: Context) {
    val storage = FirebaseStorage.getInstance()
    val imageRef = storage.getReferenceFromUrl(path)

    val localFile = File(context.getExternalFilesDir(Environment.DIRECTORY_DOWNLOADS), "flower.jpg")

    imageRef.getFile(localFile).addOnSuccessListener {
        // Local temp file has been created
        println("DOWNLOAD COMPLETED")
    }.addOnFailureListener {
        // Handle any errors
        println(it)
    }
}

fun getCity(context: Context, lat: Double, lng: Double): String {
    try {
        val gcd = Geocoder(context, Locale.getDefault())
        val addresses = gcd.getFromLocation(lat, lng, 1)
        if (addresses.size > 0 && addresses[0].locality != null) {
            return addresses[0].locality
        } else {
            return "Unknown"
        }
    } catch (e: Exception) {
        Log.e("TAG", e.toString())
    }
    return "Unknown"
}

fun hashtags(picture: Picture): List<String> {
    return if(picture.hashtags == "") emptyList()
    else picture.hashtags.split(',')
}


