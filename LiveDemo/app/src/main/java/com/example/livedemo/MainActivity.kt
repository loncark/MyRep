package com.example.livedemo

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.livedemo.ui.theme.LiveDemoTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            LiveDemoTheme {
                TheApp()
            }
        }
    }
}

@Composable
fun TheApp() {
    val navController = rememberNavController()
    NavHost(navController, startDestination = "Screen1") {

        composable(route = "Screen1") {
            Screen1 { navController.navigate("Screen2") }
        }

        composable(route = "Screen2") { Screen2() }
    }
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    LiveDemoTheme {
        Screen1()
    }
}