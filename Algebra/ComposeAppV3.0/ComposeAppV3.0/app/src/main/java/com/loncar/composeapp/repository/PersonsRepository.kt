package com.loncar.composeapp.repository

import com.loncar.composeapp.api.PersonsApi
import com.loncar.composeapp.model.Person
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import javax.inject.Inject

class PersonsRepository @Inject constructor(
    private val personsApi: PersonsApi
){
    suspend fun getPersons(): List<Person> {
        return withContext(Dispatchers.IO) {
            personsApi.getPersons().values.toList()
        }
    }
}