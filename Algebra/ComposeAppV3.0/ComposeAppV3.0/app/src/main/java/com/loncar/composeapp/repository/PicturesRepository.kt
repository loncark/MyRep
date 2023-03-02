package com.loncar.composeapp.repository

import com.loncar.composeapp.api.PicturesApi
import com.loncar.composeapp.model.Picture
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import javax.inject.Inject

class PicturesRepository @Inject constructor(
    private val picturesApi: PicturesApi
) {
    suspend fun getPictures(): List<Picture> {
        return withContext(Dispatchers.IO) {
            picturesApi.getPictures().values.toList()
        }
    }
}