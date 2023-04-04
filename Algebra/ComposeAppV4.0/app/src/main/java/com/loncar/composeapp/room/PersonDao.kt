package com.loncar.composeapp.room

import androidx.room.*
import com.loncar.composeapp.model.Person

@Dao
interface PersonDao {
    @Query("SELECT * FROM persons_table")
    suspend fun getAllPersons() : List<Person>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun addAll(persons: List<Person>)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertPerson(person: Person)

    @Update
    suspend fun update(person: Person)
}