package com.loncar.composeapp.room

import androidx.room.Database
import androidx.room.RoomDatabase
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.model.Picture

@Database(entities = [Picture::class, Person::class], version = 1, exportSchema = false)
abstract class AppDatabase : RoomDatabase() {
    abstract fun pictureDao() : PictureDao
    abstract fun personDao() : PersonDao
}