package com.loncar.composeapp.view.nav

import android.content.Context
import android.widget.Toast
import androidx.navigation.NavGraphBuilder
import androidx.navigation.NavHostController
import androidx.navigation.compose.composable
import androidx.navigation.navigation
import com.loncar.composeapp.R
import com.loncar.composeapp.view.AuthScreen
import com.loncar.composeapp.view.main.AuthenticationScreen
import com.loncar.composeapp.viewmodel.AuthenticationViewModel
import com.loncar.composeapp.viewmodel.PersonsViewModel

fun NavGraphBuilder.authNavGraph(
    navController: NavHostController,
    authenticationViewModel: AuthenticationViewModel,
    personsViewModel: PersonsViewModel,
    context: Context
) {
    navigation(
        route = Graph.AUTH,
        startDestination = AuthScreen.Login.route
    ) {

        composable(route = AuthScreen.Login.route) {
            AuthenticationScreen(
                onLogin = {
                    authenticationViewModel.logIn(
                        onSuccess = {
                            navController.popBackStack()
                            val currentUserHandle = personsViewModel.personsState.value.persons.find {
                                it.email == authenticationViewModel.authenticationState.value.email
                            }!!.handle
                            personsViewModel.setCurrentUserHandle(currentUserHandle)
                            authenticationViewModel.clear()
                            navController.navigate(Graph.MAIN)
                        },
                        onFail = {
                            Toast.makeText(context, context.getString(R.string.unable_to_login), Toast.LENGTH_SHORT).show()
                        }
                    )
                },
                onRegister = {
                    navController.popBackStack()
                    navController.navigate(AuthScreen.Register.route)
                },
                onAnonymous = {
                    personsViewModel.setCurrentUserHandle(null)
                    navController.navigate(Graph.MAIN)
                },
                authenticationState = authenticationViewModel.authenticationState.value,
                onEmailChanged = { authenticationViewModel.onEmailChanged(it) },
                onPasswordChanged = { authenticationViewModel.onPasswordChanged(it) },
                onHandleChanged = { authenticationViewModel.onHandleChanged(it) }
            )
        }

        composable(route = AuthScreen.Register.route) {
            AuthenticationScreen(
                onLogin = {
                    navController.popBackStack()
                    navController.navigate(AuthScreen.Login.route)
                },
                onRegister = {
                    if (authenticationViewModel.areHandleAndEmailUnique(
                            authenticationViewModel.authenticationState.value.handle,
                            authenticationViewModel.authenticationState.value.email
                    )) {
                        // create new Person and upload it to Firebase Database
                        personsViewModel.updatePersonsDatabase(authenticationViewModel.authenticationState.value)
                        // then create new user in Firebase Authentication
                        authenticationViewModel.register(
                            onSuccess = {
                                navController.popBackStack()
                                personsViewModel.setCurrentUserHandle(authenticationViewModel.authenticationState.value.handle)
                                authenticationViewModel.clear()
                                navController.navigate(Graph.MAIN)
                            },
                            onFail = { Toast.makeText(context, context.getString(R.string.unable_to_register), Toast.LENGTH_SHORT).show() }
                        )
                    } else {
                        Toast.makeText(context, context.getString(R.string.repetitive_handle), Toast.LENGTH_SHORT).show()
                    }
                },
                onAnonymous = {/*needs to be empty*/},
                authenticationState = authenticationViewModel.authenticationState.value,
                onEmailChanged = { authenticationViewModel.onEmailChanged(it) },
                onPasswordChanged = { authenticationViewModel.onPasswordChanged(it) },
                onHandleChanged = { authenticationViewModel.onHandleChanged(it) },
                isLogin = false
            )
        }
    }
}