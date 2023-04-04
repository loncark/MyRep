package com.loncar.composeapp.repository

import android.util.Log
import com.loncar.composeapp.api.PicturesApi
import com.loncar.composeapp.di.IODispatcher
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.room.PictureDao
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.CoroutineExceptionHandler
import kotlinx.coroutines.withContext
import retrofit2.HttpException
import java.net.ConnectException
import java.net.UnknownHostException
import javax.inject.Inject

class PicturesRepository @Inject constructor(
    private val picturesApi: PicturesApi,
    private val pictureDao: PictureDao,
    @IODispatcher private val dispatcher: CoroutineDispatcher   // testing purposes
) {
    suspend fun getPicturesAndUpdateLocalDatabase(): List<Picture> {
        return withContext(dispatcher) {    // Dispatchers.IO before testing
            try {
                val pictures = picturesApi.getPictures().values.toList()
                pictureDao.addAll(pictures)
                Log.e("TAG", "Went to internet")
                return@withContext pictures
            } catch (e: Exception) {
                Log.e("TAG", "Went to local database")
                when(e) {
                    is UnknownHostException,
                    is ConnectException,
                    is HttpException -> {
                        return@withContext pictureDao.getAllPictures()
                    }
                    else -> {
                        Log.e("TAG", e.toString())
                        return@withContext pictureDao.getAllPictures()
                    }
                }
            }
        }
    }
}