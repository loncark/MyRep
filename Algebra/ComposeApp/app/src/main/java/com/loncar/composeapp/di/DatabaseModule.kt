package com.loncar.composeapp.di

import android.content.Context
import androidx.room.Room
import com.loncar.composeapp.room.AppDatabase
import com.loncar.composeapp.room.PersonDao
import com.loncar.composeapp.room.PictureDao
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object DatabaseModule {

    @Provides
    @Singleton
    fun provideDatabase(@ApplicationContext context: Context) : AppDatabase {
        return Room.databaseBuilder(context, AppDatabase::class.java, "app_database").build()
    }

    @Provides
    @Singleton
    fun providePictureDao(database: AppDatabase) : PictureDao {
        return database.pictureDao()
    }

    @Provides
    @Singleton
    fun providePersonDao(database: AppDatabase) : PersonDao {
        return database.personDao()
    }
}