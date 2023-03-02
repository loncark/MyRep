package com.loncar.composeapp.model

@kotlinx.serialization.Serializable
data class Picture(
    val id: String,
    val handle: String,
    var description: String,
    var resource: String,
    val lat: String,
    val lng: String,
    val hashtags : String
)

// consult picturesSetup.py for a json of dummy pictures