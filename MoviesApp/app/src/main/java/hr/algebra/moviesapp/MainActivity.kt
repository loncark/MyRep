package hr.algebra.moviesapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.material.Surface
import androidx.compose.material.TextField
import androidx.compose.runtime.*
import androidx.lifecycle.viewmodel.compose.viewModel
import hr.algebra.moviesapp.ui.theme.MoviesAppTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MoviesAppTheme {
                // A surface container using the 'background' color from the theme
                Surface {
                    val nameViewModel = viewModel<NameViewModel>()

                    val name by nameViewModel.name

                    CustomTextField(name, onNameChanged = { name = it })
                }
            }
        }
    }
}

@Composable
fun CustomTextField(name: String, onNameChanged: (String) -> Unit) {
    TextField(value = name, onValueChange = onNameChanged)
}
