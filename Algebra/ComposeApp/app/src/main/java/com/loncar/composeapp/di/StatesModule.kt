package com.loncar.composeapp.di

import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import com.loncar.composeapp.viewmodel.*
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module     // instructs Hilt on how to provide state dependencies
@InstallIn(SingletonComponent::class)       // lifetime of the module equals the lifetime of the app
object StatesModule {

    @Provides
    @Singleton
    fun providePicturesState() : MutableState<PicturesState> {
        return mutableStateOf(PicturesState())
    }

    @Provides
    @Singleton
    fun providePersonsState() : MutableState<PersonsState> {
        return mutableStateOf(PersonsState())
    }

    @Provides
    @Singleton
    fun provideAuthenticationState() : MutableState<AuthenticationState> {
        return mutableStateOf(AuthenticationState())
    }

    @Provides
    @Singleton
    fun provideSearchState() : MutableState<SearchState> {
        return mutableStateOf(SearchState())
    }

    @Provides
    @Singleton
    fun provideUploadState() : MutableState<UploadState> {
        return mutableStateOf(UploadState())
    }
}