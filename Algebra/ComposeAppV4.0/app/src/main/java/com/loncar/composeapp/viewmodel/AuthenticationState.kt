package com.loncar.composeapp.viewmodel

data class AuthenticationState(
    val email: String = "",
    val password: String = "",
    val isEmailValid: Boolean = false,
    val isPasswordValid: Boolean = false,
    val handle: String = ""
)
