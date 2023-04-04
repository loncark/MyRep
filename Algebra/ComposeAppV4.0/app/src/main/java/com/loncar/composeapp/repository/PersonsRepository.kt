package com.loncar.composeapp.repository

import com.loncar.composeapp.api.PersonsApi
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.room.PersonDao
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import retrofit2.HttpException
import java.net.ConnectException
import java.net.UnknownHostException
import javax.inject.Inject

class PersonsRepository @Inject constructor(
    private val personsApi: PersonsApi,
    private val personDao: PersonDao
){
    suspend fun getPersonsAndUpdateLocalDatabase(): List<Person> {
        return withContext(Dispatchers.IO) {
            try {
                val persons = personsApi.getPersons().values.toList()
                personDao.addAll(persons)
                return@withContext persons
            } catch (e: Exception) {
                when(e) {
                    is UnknownHostException,
                    is ConnectException,
                    is HttpException -> {
                        return@withContext personDao.getAllPersons()
                    }
                    else -> throw e
                }
            }

        }
    }
}