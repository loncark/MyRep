package com.loncar.composeapp.view

import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.Home
import androidx.compose.material.icons.filled.Person
import androidx.compose.ui.graphics.vector.ImageVector
import com.loncar.composeapp.R

sealed class BottomNavScreen(
    val route: String,
    val title: Int,
    val icon: ImageVector
) {
    object Home: BottomNavScreen(
        route = "home",
        title = R.string.home,
        icon = Icons.Default.Home
    )
    object Upload: BottomNavScreen(
        route = "upload",
        title = R.string.upload,
        icon = Icons.Default.Add
    )
    object Profile: BottomNavScreen(
        route = "profile",
        title = R.string.profile,
        icon = Icons.Default.Person
    )
}
