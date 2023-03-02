package com.loncar.composeapp.viewmodel

import android.net.Uri
import android.util.Log
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineExceptionHandler
import javax.inject.Inject

@HiltViewModel
class UploadViewModel @Inject constructor(
    private val _uploadState : MutableState<UploadState>,
) : ViewModel() {
    val uploadState : State<UploadState> get() = _uploadState      // makes state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("UPLOAD_VIEWMODEL", e.toString(), e)
    }

    fun onDescriptionChanged(description: String) {
        _uploadState.value = _uploadState.value.copy(   // fetch using value
            description = description
        )
    }

    fun onHashtagsChanged(hashtags: String) {
        _uploadState.value = _uploadState.value.copy(   // fetch using value
            hashtags = hashtags
        )
    }

    fun onUriChanged(uri: Uri?) {
        _uploadState.value = _uploadState.value.copy(   // fetch using value
            uri = uri
        )
    }

    fun clear() {
        _uploadState.value = _uploadState.value.copy(
            description = "",
            hashtags = "",
            uri = null
        )
    }
}