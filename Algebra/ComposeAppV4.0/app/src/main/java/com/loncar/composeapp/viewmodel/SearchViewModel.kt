package com.loncar.composeapp.viewmodel

import android.util.Log
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineExceptionHandler
import javax.inject.Inject

@HiltViewModel
class SearchViewModel @Inject constructor(
    private val _searchState : MutableState<SearchState>
) : ViewModel() {
    val searchState: State<SearchState> get() = _searchState   // makes the state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("SEARCH_VIEWMODEL", e.toString(), e)
    }

    fun onInputChanged(input: String) {
        _searchState.value = _searchState.value.copy(   // fetch using value
            input = input,
        )
    }

    fun clear() {
        _searchState.value = _searchState.value.copy(
            input = ""
        )
    }
}