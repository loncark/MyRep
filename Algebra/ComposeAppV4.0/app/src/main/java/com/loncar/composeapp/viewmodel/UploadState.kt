package com.loncar.composeapp.viewmodel

import android.net.Uri

data class UploadState(
    val description : String = "",
    val hashtags : String = "",
    val uri : Uri? = null,
    val isUpdate: Boolean = false,
    val pictureToUpdateId : Int = 0,
    val pictureToUpdateResource : String? = null,        // not the same function as uri
    val filter : Filter = Filter.NONE
)

enum class Filter {
    GRAYSCALE, SEPIA, NONE
}

val sepiaMatrix = floatArrayOf(
    0.393f, 0.769f, 0.189f, 0f, 0f,
    0.349f, 0.686f, 0.168f, 0f, 0f,
    0.272f, 0.534f, 0.131f, 0f, 0f,
    0f, 0f, 0f, 1f, 0f
)
