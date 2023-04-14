package com.loncar.composeapp.view.nav

import android.widget.Toast
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import com.loncar.composeapp.view.MainScreen
import com.loncar.composeapp.viewmodel.AuthenticationViewModel
import com.loncar.composeapp.viewmodel.PersonsViewModel

@Composable     // graph = big navigation unit
fun RootNavGraph(rootController: NavHostController) {
    val authenticationViewModel = hiltViewModel<AuthenticationViewModel>()
    val personsViewModel = hiltViewModel<PersonsViewModel>()
    val context = LocalContext.current

    NavHost(
        navController = rootController,
        startDestination = Graph.AUTH,
        route = Graph.ROOT
    ) {
        authNavGraph(navController = rootController, authenticationViewModel, personsViewModel, context)
        composable(route = Graph.MAIN) {
            authenticationViewModel.clear()
            Toast.makeText(context, "Logged in as @${personsViewModel.personsState.value.currentUserHandle}", Toast.LENGTH_SHORT).show()
            MainScreen(rootController)
        }
    }
}