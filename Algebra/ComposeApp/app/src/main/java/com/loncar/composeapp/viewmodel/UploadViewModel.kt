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
        _uploadState.value = _uploadState.value.copy(
            hashtags = hashtags
        )
    }

    fun onUriChanged(uri: Uri?) {
        _uploadState.value = _uploadState.value.copy(
            uri = uri
        )
    }

    fun setIsUpdate(bool: Boolean) {
        _uploadState.value = _uploadState.value.copy(
            isUpdate = bool
        )
    }

    fun setFilter(flt: Filter) {
        _uploadState.value = _uploadState.value.copy(
            filter = flt
        )
    }

    fun setPictureToUpdateResource(it: String) {
        _uploadState.value = _uploadState.value.copy(
            pictureToUpdateResource = it
        )
    }

    fun setPictureToUpdateId(id: Int) {
        _uploadState.value = _uploadState.value.copy(
            pictureToUpdateId = id
        )
    }

    fun clear() {
        _uploadState.value = _uploadState.value.copy(
            description = "",
            hashtags = "",
            uri = null,
            isUpdate = false
        )
    }
}