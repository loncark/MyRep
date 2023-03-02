package com.loncar.composeapp.view.nav

import android.widget.Toast
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavHostController
import androidx.navigation.NavType
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.navArgument
import com.loncar.composeapp.R
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.view.AuthScreen
import com.loncar.composeapp.view.BottomNavScreen
import com.loncar.composeapp.view.common.getCity
import com.loncar.composeapp.view.main.*
import com.loncar.composeapp.viewmodel.*

@Composable
fun BottomNavGraph(navController: NavHostController, rootController: NavHostController) {

    val picturesVM = hiltViewModel<PicturesViewModel>()
    val personsVM = hiltViewModel<PersonsViewModel>()
    val searchVM = hiltViewModel<SearchViewModel>()
    val uploadVM = hiltViewModel<UploadViewModel>()

    // Always pass STATES, not variables! (Except for context.)
    val context = LocalContext.current

    NavHost(
        navController = navController,
        startDestination = BottomNavScreen.Home.route
    ) {
        // navigation between bottom bar icons
        composable(route = BottomNavScreen.Home.route) {
            HomeScreen(
                picturesState = picturesVM.picturesState.value,
                currentUserHandle = personsVM.personsState.value.currentUserHandle,
                searchState = searchVM.searchState.value,
                onItemClick = { navController.navigate("Picture/$it") },
                onInputChanged = { searchVM.onInputChanged(it) },
                onSearch = {
                    navController.navigate(BottomNavScreen.Home.route)
                }
            )
        }
        composable(route = BottomNavScreen.Upload.route) {
            UploadScreen(
                uploadVM.uploadState.value,
                personsVM.personsState.value.currentUserHandle,
                onDescriptionChanged = { uploadVM.onDescriptionChanged(it) },
                onHashtagsChanged = { uploadVM.onHashtagsChanged(it) },
                onUriChanged = { uploadVM.onUriChanged(it) },
                onUpload = {
                    Toast.makeText(context, context.getString(R.string.uploading_picture), Toast.LENGTH_LONG).show()
                    picturesVM.createAndUploadNewPicture(uploadVM.uploadState.value, personsVM.personsState.value.currentUserHandle!!)
                    navController.popBackStack()
                    uploadVM.clear()
                    navController.navigate(BottomNavScreen.Profile.route)
                }
            )
        }
        composable(route = BottomNavScreen.Profile.route) {
            UserScreen(
                handle = personsVM.personsState.value.currentUserHandle,
                picturesState = picturesVM.picturesState.value,
                personsState = personsVM.personsState.value,
                onItemClick = { navController.navigate("${BottomNavScreen.Profile.route}/$it") },
                onLogOut = {
                    // DOES NOT WORK
                    rootController.popBackStack()
                    personsVM.setCurrentUserHandle(null)
                    rootController.navigate(Graph.AUTH)
                }
            )
        }

        // navigation to a picture tapped on Home or Discover screen
        composable(
            route = "Picture/{id}",
            arguments = listOf(navArgument("id") { type = NavType.IntType })
        ) { NavBackStackEntry ->    // allows to reach the passed id argument
            val pict =
                picturesVM.picturesState.value.pictures.find { it.id.toInt() == NavBackStackEntry.arguments?.getInt("id") }
            PictureScreen(
                picture = pict!!,
                onPersonClick = { userHandle -> navController.navigate("User/${userHandle}") },
                onLocationClick = { navController.navigate("Map/$it") }
            )
        }

        // navigation to a picture tapped on User screen
        composable(
            route = "${BottomNavScreen.Profile.route}/{id}",
            arguments = listOf(navArgument("id") { type = NavType.IntType })
        ) { NavBackStackEntry ->
            val pict =
                picturesVM.picturesState.value.pictures.find { it.id.toInt() == NavBackStackEntry.arguments?.getInt("id") }
            PictureScreen(
                picture = pict!!,
                onPersonClick = {/* This needs to be empty*/ },
                onLocationClick = { navController.navigate("Map/$it") }
            )
        }

        // navigation to a user screen that is not of a logged in user
        composable(
            route = "User/{userHandle}",
            arguments = listOf(navArgument("userHandle") { type = NavType.StringType })
        ) { NavBackStackEntry ->
            val handle = NavBackStackEntry.arguments?.getString("userHandle")
            UserScreen(
                handle = handle!!,
                personsState = personsVM.personsState.value,
                picturesState = picturesVM.picturesState.value,
                onItemClick = { navController.navigate("User/${handle}/$it") },
                onLogOut = {/* needs to be empty*/}
            )
        }

        // and to a picture tapped on that profile
        composable(
            route = "User/{userHandle}/{id}",
            arguments = listOf(
                navArgument("userHandle") { type = NavType.StringType },
                navArgument("id") { type = NavType.IntType }
            )
        ) { NavBackStackEntry ->
            val pict = picturesVM.picturesState.value.pictures.find {
                it.handle == NavBackStackEntry.arguments?.getString("userHandle")
                        && it.id.toInt() == NavBackStackEntry.arguments?.getInt("id")
            }
            PictureScreen(
                picture = pict!!,
                onPersonClick = {/* This needs to be empty*/ },
                onLocationClick = { navController.navigate("Map/$it") }
            )
        }

        // navigation to MapScreen
        composable(
            route = "Map/{id}",
            arguments = listOf(navArgument("id") { type = NavType.IntType })
        ) { NavBackStackEntry ->    // to obtain id of the pic that map will focus on
            val currentPicture =
                picturesVM.picturesState.value.pictures.find { it.id.toInt() == NavBackStackEntry.arguments!!.getInt("id") }
            val cityOfCurrentPicture = getCity(
                LocalContext.current,
                currentPicture!!.lat.toDouble(),
                currentPicture.lng.toDouble()
            )

            val cityPictures = mutableListOf<Picture>()
            picturesVM.picturesState.value.pictures.forEach {
                if (getCity(
                        LocalContext.current,
                        it.lat.toDouble(),
                        it.lng.toDouble()
                    ) == cityOfCurrentPicture
                ) {
                    cityPictures.add(it)
                }
            }

            MapScreen(
                pictures = cityPictures,
                id = NavBackStackEntry.arguments!!.getInt("id"),
                onMarkerClick = {
                    navController.navigate("Picture/$it")
                }
            )
        }
    }
}