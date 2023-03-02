package com.loncar.composeapp.viewmodel

import android.net.Uri

data class UploadState(
    val description : String = "",
    val hashtags : String = "",
    val uri : Uri? = null,
)
