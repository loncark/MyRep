package com.loncar.composeapp.viewmodel

import com.loncar.composeapp.model.Picture

data class PicturesState(
    val pictures: List<Picture> = emptyList(),
    val loading: Boolean = true
)
