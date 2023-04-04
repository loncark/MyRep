package com.loncar.composeapp.di

import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import kotlinx.coroutines.CoroutineDispatcher
import kotlinx.coroutines.Dispatchers
import javax.inject.Qualifier

@Qualifier      // allows us to provide different dispatchers to the CoroutineDispatcher dependencies
@Retention(AnnotationRetention.BINARY)
annotation class MainDispatcher

@Qualifier
@Retention(AnnotationRetention.BINARY)
annotation class IODispatcher

@Module
@InstallIn(SingletonComponent::class)
object DispatcherModule {

    @MainDispatcher
    @Provides
    fun providesMainDispatcher() : CoroutineDispatcher = Dispatchers.Main

    @IODispatcher
    @Provides
    fun providesIODispatcher() : CoroutineDispatcher = Dispatchers.IO
}