package com.loncar.composeapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.material.Surface
import androidx.navigation.compose.rememberNavController
import com.google.firebase.FirebaseApp
import com.loncar.composeapp.ui.theme.ComposeAppTheme
import com.loncar.composeapp.view.nav.RootNavGraph
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint      // IF LAUNCH CRASHES, REMOVE THIS, RUN THE APP, LET IT FAIL THEN ADD THIS BACK AND RUN AGAIN
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            ComposeAppTheme(false) {
                Surface {
                    FirebaseApp.initializeApp(this)
                    RootNavGraph(rootController = rememberNavController())
                }
            }
        }
    }
}

/*
@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    ComposeAppTheme {
        HomeScreen()
        val str = "Today is a good day. This is a picture description it should fit nicely into the composable."
        PictureScreen(Picture("handle", str, R.drawable.ic_launcher_background, false, "New York"))

    }
}*/