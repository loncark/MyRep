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
import com.loncar.composeapp.logger.LogOutLogger
import com.loncar.composeapp.model.Picture
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
            HomeScreen(     // null if no internet
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
                    picturesVM.createAndUploadNewPictureToFirebase(
                        uploadVM.uploadState.value,
                        personsVM.personsState.value.currentUserHandle!!,
                        context,
                        noConnectionToast = {
                            Toast.makeText(context, context.getString(R.string.noConnection), Toast.LENGTH_SHORT).show()
                        },
                        uploadSuccessfulToast = {
                            Toast.makeText(context, context.getString(R.string.upload_successful), Toast.LENGTH_SHORT).show()
                        },
                        noPictureSelectedToast = {
                            Toast.makeText(context, context.getString(R.string.no_picture_selected), Toast.LENGTH_SHORT).show()
                        }
                    )
                    navController.popBackStack()
                    uploadVM.clear()
                    navController.navigate(BottomNavScreen.Profile.route)
                },
                onUpdate = {
                    picturesVM.updatePicture(
                        uploadState = uploadVM.uploadState.value,
                        currentUserHandle = personsVM.personsState.value.currentUserHandle!!,
                        updateSuccessfulToast = {
                            Toast.makeText(context, context.getString(R.string.update_successful), Toast.LENGTH_SHORT).show()
                        },
                        noConnectionToast = {
                            Toast.makeText(context, context.getString(R.string.noConnection), Toast.LENGTH_SHORT).show()
                        }
                    )
                    uploadVM.clear()
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Profile.route)
                },
                onCancel = {
                    uploadVM.clear()
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Profile.route)
                },
                onFilterChanged = {
                    uploadVM.setFilter(it)
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
                    rootController.popBackStack()
                    searchVM.clear()
                    LogOutLogger().templatePrint(personsVM.personsState.value.currentUserHandle!!)
                    personsVM.setCurrentUserHandle(null)
                    rootController.navigate(Graph.AUTH)
                }
            )
        }

        // navigation to a picture tapped on Home screen
        composable(
            route = "Picture/{id}",
            arguments = listOf(navArgument("id") { type = NavType.IntType })
        ) { NavBackStackEntry ->    // allows to reach the passed id argument
            val pict =
                picturesVM.picturesState.value.pictures.find { it.id.toInt() == NavBackStackEntry.arguments?.getInt("id") }
            PictureScreen(
                picture = pict!!,
                currentUserHandle = personsVM.personsState.value.currentUserHandle,
                onPersonClick = { userHandle -> navController.navigate("User/${userHandle}") },
                onLocationClick = { navController.navigate("Map/$it") },
                onDelete = { _, _ -> /*swipe won't be enabled anyway, so do nothing*/ },
                onUpdate = { _, _ -> /*should be empty*/}
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
                currentUserHandle = personsVM.personsState.value.currentUserHandle,
                onPersonClick = {/* This needs to be empty*/ },
                onLocationClick = { navController.navigate("Map/$it") },
                onDelete = { id, url ->
                    picturesVM.deletePictureFromFirebase(
                        id = id,
                        url = url,
                        currentUserHandle = personsVM.personsState.value.currentUserHandle!!,
                        deleteSuccessful = { Toast.makeText(context, context.getString(R.string.delete_successful), Toast.LENGTH_SHORT).show() },
                        noConnectionToast = { Toast.makeText(context, context.getString(R.string.noConnection), Toast.LENGTH_SHORT).show() }
                    )
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Profile.route)
                },
                onUpdate = { id, resource ->
                    uploadVM.setIsUpdate(true)
                    uploadVM.setPictureToUpdateId(id)
                    uploadVM.setPictureToUpdateResource(resource)
                    uploadVM.onDescriptionChanged(pict.description)
                    uploadVM.onHashtagsChanged(pict.hashtags)
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Upload.route)
                }
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
                currentUserHandle = personsVM.personsState.value.currentUserHandle,
                onPersonClick = {/* This needs to be empty*/ },
                onLocationClick = { navController.navigate("Map/$it") },
                onDelete = { id, url ->
                    picturesVM.deletePictureFromFirebase(
                        id = id,
                        url = url,
                        currentUserHandle = personsVM.personsState.value.currentUserHandle!!,
                        deleteSuccessful = { Toast.makeText(context, context.getString(R.string.delete_successful), Toast.LENGTH_SHORT).show() },
                        noConnectionToast = { Toast.makeText(context, context.getString(R.string.noConnection), Toast.LENGTH_SHORT).show() }
                    )
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Profile.route)
                },
                onUpdate = { id, resource ->
                    uploadVM.setIsUpdate(true)
                    uploadVM.setPictureToUpdateId(id)
                    uploadVM.setPictureToUpdateResource(resource)
                    uploadVM.onDescriptionChanged(pict.description)
                    uploadVM.onHashtagsChanged(pict.hashtags)
                    navController.popBackStack()
                    navController.navigate(BottomNavScreen.Upload.route)
                }
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