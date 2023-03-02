package com.loncar.composeapp.viewmodel

import com.loncar.composeapp.model.Person

data class PersonsState(
    val persons: List<Person> = emptyList(),
    var currentUserHandle: String? = null,
    val loading: Boolean = true,
)
