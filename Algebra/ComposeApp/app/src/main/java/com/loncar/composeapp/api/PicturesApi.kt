package com.loncar.composeapp.api

import com.loncar.composeapp.model.Picture
import retrofit2.http.GET
import retrofit2.http.POST

interface PicturesApi {
    @GET("/pictures.json")
    suspend fun getPictures(): Map<String, Picture>
}