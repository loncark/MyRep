package com.loncar.composeapp.di

import com.jakewharton.retrofit2.converter.kotlinx.serialization.asConverterFactory
import com.loncar.composeapp.api.PersonsApi
import com.loncar.composeapp.api.PicturesApi
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import kotlinx.serialization.ExperimentalSerializationApi
import kotlinx.serialization.json.Json
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import java.util.concurrent.TimeUnit
import javax.inject.Singleton

private const val FIREBASE_URL = "https://composeapp-47d09-default-rtdb.europe-west1.firebasedatabase.app/"

@Module     // instructs Hilt on how to provide dependencies of okHttpClient, PersonsApi and PicturesApi
@InstallIn(SingletonComponent::class)       // lifetime of the module equals the lifetime of the app
object NetworkModule {

    @Provides
    @Singleton      // created at - Application#onCreate, destroyed at - Application#onDestroy
    fun provideHttpClient(): OkHttpClient {
        return OkHttpClient.Builder()
            .readTimeout(10, TimeUnit.SECONDS)
            .connectTimeout(10, TimeUnit.SECONDS)
            .build()
    }

    @Provides
    @Singleton          // anytime a PersonApi is asked, the same instance will be provided
    @ExperimentalSerializationApi
    fun providePersonsApi(okHttpClient: OkHttpClient): PersonsApi {
        val json = Json {
            ignoreUnknownKeys = true
        }
        return Retrofit.Builder()
            .baseUrl(FIREBASE_URL)
            .client(okHttpClient)
            .addConverterFactory(json.asConverterFactory("application/json".toMediaType()))
            .build()
            .create(PersonsApi::class.java)
    }

    @Provides
    @Singleton
    @ExperimentalSerializationApi
    fun providePicturesApi(okHttpClient: OkHttpClient): PicturesApi {
        val json = Json {
            ignoreUnknownKeys = true
        }
        return Retrofit.Builder()
            .baseUrl(FIREBASE_URL)
            .client(okHttpClient)
            .addConverterFactory(json.asConverterFactory("application/json".toMediaType()))
            .build()
            .create(PicturesApi::class.java)
    }
}