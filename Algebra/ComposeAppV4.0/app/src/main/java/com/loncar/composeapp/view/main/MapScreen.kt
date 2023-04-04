package com.loncar.composeapp.view.main

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import com.google.android.gms.maps.model.CameraPosition
import com.google.android.gms.maps.model.LatLng
import com.google.maps.android.compose.*
import com.loncar.composeapp.R
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.view.common.bitmapDescriptorFromVector

@Composable
fun MapScreen(pictures: List<Picture>, id: Int, onMarkerClick : (id:Int)->Unit) {

    val points = mutableMapOf<Int, LatLng>()
    pictures.forEach {
        points[it.id.toInt()] = LatLng(it.lat.toDouble(), it.lng.toDouble())
    }

    // id of the picture that needs to be zoomed in on
    val cameraPositionState = rememberCameraPositionState {
        position = CameraPosition.fromLatLngZoom(points[id]!!, 12f)
    }

    val uiSettings by remember {
        mutableStateOf(MapUiSettings(zoomControlsEnabled = false))
    }

    val properties by remember {
        mutableStateOf(MapProperties(mapType = MapType.HYBRID, isTrafficEnabled = true))
    }

    GoogleMap(
        modifier = Modifier.fillMaxSize(),
        cameraPositionState = cameraPositionState,
        uiSettings = uiSettings,
        properties = properties
    ) {
        points.forEach { point ->
            Marker(
                icon = bitmapDescriptorFromVector(
                    LocalContext.current,
                    R.drawable.location
                ),
                position = point.value,
                onClick = {
                    onMarkerClick(point.key)
                    true
                }
            )
        }
    }
}
