package com.loncar.composeapp.view.main

import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.core.*
import androidx.compose.animation.fadeIn
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Person
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.rotate
import androidx.compose.ui.focus.FocusDirection
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.unit.dp
import com.loncar.composeapp.R
import com.loncar.composeapp.view.common.AnimatedIconButton
import com.loncar.composeapp.viewmodel.AuthenticationState

@Composable
fun AuthenticationScreen(
    authenticationState: AuthenticationState,
    onLogin: () -> Unit,
    onRegister: () -> Unit,
    onEmailChanged: (String) -> Unit,
    onPasswordChanged: (String) -> Unit,
    onHandleChanged: (String) -> Unit,
    onAnonymous: () -> Unit,
    modifier: Modifier = Modifier,
    isLogin: Boolean = true
) {

    val scrollState = rememberScrollState()
    val focusManager = LocalFocusManager.current

    val infiniteTransition = rememberInfiniteTransition()
    val angle by infiniteTransition.animateFloat(
        initialValue = 0f,
        targetValue = 360f,
        animationSpec = infiniteRepeatable(
            animation = tween(5500, easing = LinearEasing),
            repeatMode = RepeatMode.Restart
        )
    )

    val state = remember {
        MutableTransitionState(false).apply {
            targetState = true
        }
    }

    AnimatedVisibility(
        visibleState = state,
        enter = fadeIn(animationSpec = tween(durationMillis = 1000))
    ) {

        Column(
            modifier = modifier
                .fillMaxSize()
                .verticalScroll(scrollState),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.Bottom
        ) {
            var icon = R.drawable.flower_icon_blue
            if (!isLogin) {
                icon = R.drawable.flower_icon_red
            }

            Image(
                painter = painterResource(id = icon),
                contentDescription = stringResource(R.string.authentication),
                modifier = Modifier
                    .size(270.dp)
                    .rotate(angle)
            )
            Card(
                modifier = modifier
                    .padding(vertical = 30.dp)
                    .fillMaxWidth()
                    .padding(horizontal = 12.dp),
                shape = RoundedCornerShape(size = 9.dp),
                border = BorderStroke(width = 1.dp, color = MaterialTheme.colors.primary)
            ) {
                Column(
                    modifier = modifier.padding(all = 12.dp),
                    horizontalAlignment = Alignment.CenterHorizontally,
                    verticalArrangement = Arrangement.spacedBy(9.dp)
                ) {

                    OutlinedTextField(
                        modifier = modifier.fillMaxWidth(),
                        value = authenticationState.email,
                        onValueChange = onEmailChanged,
                        label = {
                            Text(
                                text = stringResource(id = R.string.email_address),
                                style = MaterialTheme.typography.body1
                            )
                        },
                        keyboardOptions = KeyboardOptions(
                            keyboardType = KeyboardType.Email,
                            imeAction = ImeAction.Next
                        ),
                        keyboardActions = KeyboardActions(
                            onNext = { focusManager.moveFocus(FocusDirection.Down) }
                        ),
                        isError = !authenticationState.isEmailValid
                    )

                    if (!isLogin) {
                        OutlinedTextField(
                            modifier = modifier.fillMaxWidth(),
                            value = authenticationState.handle,
                            onValueChange = onHandleChanged,
                            label = {
                                Text(
                                    text = stringResource(id = R.string.handle),
                                    style = MaterialTheme.typography.body1
                                )
                            },
                            keyboardOptions = KeyboardOptions(
                                keyboardType = KeyboardType.Text,
                                imeAction = ImeAction.Next
                            ),
                            keyboardActions = KeyboardActions(
                                onNext = { focusManager.moveFocus(FocusDirection.Down) }
                            )
                        )
                    }

                    OutlinedTextField(
                        modifier = modifier.fillMaxWidth(),
                        value = authenticationState.password,
                        onValueChange = onPasswordChanged,
                        label = {
                            Text(
                                text = stringResource(id = R.string.password),
                                style = MaterialTheme.typography.body1
                            )
                        },
                        keyboardOptions = KeyboardOptions(
                            keyboardType = KeyboardType.Password,
                            imeAction = ImeAction.Done
                        ),
                        keyboardActions = KeyboardActions(
                            onDone = { focusManager.clearFocus() }
                        ),
                        isError = !authenticationState.isPasswordValid,
                        visualTransformation = PasswordVisualTransformation()
                    )

                    Button(
                        modifier = modifier.fillMaxWidth(),
                        content = {
                            Text(
                                if (isLogin) stringResource(id = R.string.login) else
                                    stringResource(id = R.string.register)
                            )
                        },
                        onClick = if (isLogin) onLogin else onRegister,
                        enabled = authenticationState.isEmailValid
                                && authenticationState.isPasswordValid,
                        colors = ButtonDefaults.buttonColors(MaterialTheme.colors.secondary)
                    )

                    if (isLogin) {
                        Row(
                            horizontalArrangement = Arrangement.SpaceBetween,
                            modifier = Modifier.fillMaxWidth()
                        ) {
                            Button(
                                onClick = onAnonymous,
                            ) {
                                Text(stringResource(id = R.string.anonymous))
                            }

                            AnimatedIconButton(
                                icon = {
                                    Icon(
                                        imageVector = Icons.Filled.Person,
                                        contentDescription = stringResource(id = R.string.person)
                                    )
                                },
                                text = {
                                    Text(stringResource(id = R.string.register))
                                },
                                onClick = onRegister
                            )
                        }
                    }

                    else {
                        AnimatedIconButton(
                            icon = {
                                Icon(
                                    imageVector = Icons.Filled.Person,
                                    contentDescription = stringResource(id = R.string.person)
                                )
                            },
                            text = {
                                Text(
                                    stringResource(id = R.string.login)
                                )
                            },
                            onClick = onLogin
                        )
                    }
                }


            }


        }
    }

}
