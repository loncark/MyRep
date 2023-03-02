package com.loncar.composeapp.viewmodel

import android.util.Log
import android.util.Patterns
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.repository.AuthenticationRepository
import com.loncar.composeapp.repository.PersonsRepository
import com.loncar.composeapp.view.common.isValidPassword
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class AuthenticationViewModel @Inject constructor(
    private val _authenticationState : MutableState<AuthenticationState>,
    private val _personsState : MutableState<PersonsState>
) : ViewModel() {
    val authenticationState: State<AuthenticationState>  get() = _authenticationState   // makes the state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("AUTH_VIEWMODEL", e.toString(), e)
    }

    fun onEmailChanged(email: String) {
        _authenticationState.value = _authenticationState.value.copy(   // fetch using value
            email = email,
            isEmailValid = Patterns.EMAIL_ADDRESS.matcher(email).matches()
        )
    }

    fun onPasswordChanged(password: String) {
        _authenticationState.value = _authenticationState.value.copy(
            password = password,
            isPasswordValid = password.isValidPassword()
        )
    }

    fun onHandleChanged(handle: String) {
        _authenticationState.value = _authenticationState.value.copy(
            handle = handle,
        )
    }

    fun areHandleAndEmailUnique(handle: String, email: String) : Boolean {
        return _personsState.value.persons.find { it.handle == handle || it.email == email } == null
    }

    fun logIn(onSuccess: () -> Unit, onFail: () -> Unit) {
        AuthenticationRepository.logIn(
            _authenticationState.value.email,
            _authenticationState.value.password,
            onSuccess = onSuccess,
            onFail = onFail
        )
    }

    fun register(onSuccess: () -> Unit, onFail: () -> Unit) {
        AuthenticationRepository.register(
            _authenticationState.value.email,
            _authenticationState.value.password,
            onSuccess = onSuccess,
            onFail = onFail
        )
    }

    fun clear() {
        _authenticationState.value = _authenticationState.value.copy(
            email = "",
            password = "",
            isPasswordValid = false,
            isEmailValid = false,
            handle = ""
        )
    }
}