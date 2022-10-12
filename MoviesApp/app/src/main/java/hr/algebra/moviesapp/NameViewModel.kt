package hr.algebra.moviesapp

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel


class NameViewModel : ViewModel() {
    private val _name = mutableStateOf("")
    val name : State<String>
        get() = _name

}