package com.loncar.composeapp.viewmodel

import android.net.Uri
import android.util.Log
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.State
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.repository.PersonsRepository
import com.loncar.composeapp.view.common.encode
import com.loncar.composeapp.view.common.toAbsPath
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.launch
import javax.inject.Inject

@HiltViewModel
class PersonsViewModel @Inject constructor(
    private val personsRepository: PersonsRepository,
    private val _personsState : MutableState<PersonsState>
) : ViewModel() {
    val personsState: State<PersonsState>  get() = _personsState    // makes the state public

    private val errorHandler = CoroutineExceptionHandler { _, e ->
        Log.e("PERSONS_VIEWMODEL", e.toString(), e)
    }

    fun updatePersonsDatabase(authState: AuthenticationState) {

        val newPerson = Person(
            email = authState.email,
            handle = authState.handle,
            icon = "https://cdn-icons-png.flaticon.com/512/5218/5218681.png",
            bio = "A dummy bio for a new user. Edit button maybe in V5.0."
        )

        val databaseReference = FirebaseDatabase.getInstance().getReference("persons/${authState.handle}")
        databaseReference.setValue(newPerson)
            .addOnSuccessListener {
                println("JSON PERSONS SUCCESSFULLY UPDATED")
                reload()
            }
            .addOnFailureListener { error ->
                println("FAILED TO WRITE PERSON TO DATABASE: $error")
            }
    }

    fun setCurrentUserHandle(handle: String?) {
        _personsState.value = _personsState.value.copy(   // fetch using value
            currentUserHandle = handle
        )
    }

    private fun reload() {
        viewModelScope.launch(errorHandler) {
            val allPersons = personsRepository.getPersons()

            allPersons.forEach {
                it.icon = toAbsPath(it.icon)
            }
            _personsState.value = _personsState.value.copy(
                persons = allPersons,
                loading = false
            )
        }
    }

    init { reload() }
}