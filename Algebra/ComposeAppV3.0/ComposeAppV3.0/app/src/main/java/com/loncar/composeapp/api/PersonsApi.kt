package com.loncar.composeapp.api

import com.loncar.composeapp.model.Person
import retrofit2.http.GET

interface PersonsApi {
    @GET("/persons.json")
    suspend fun getPersons(): Map<String, Person>
}