package com.example.livedemo

import android.graphics.Typeface
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.material.Button
import androidx.compose.material.ButtonDefaults
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.SolidColor
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

@Composable
fun Screen1(onButtonClick: () -> Unit = {}) {

    Column(verticalArrangement = Arrangement.SpaceEvenly,
           horizontalAlignment = Alignment.CenterHorizontally,
           modifier = Modifier.fillMaxSize()) {

        Text(
            "First screen",
            color = Color.Black,
            textAlign = TextAlign.Center,
            fontSize = 30.sp,
            fontFamily = FontFamily(Typeface.SERIF),
            modifier = Modifier
                .border(BorderStroke(2.dp, SolidColor(Color.Black)))
                .padding(20.dp)
        )

        Button(
            onClick = { onButtonClick() },
            colors = ButtonDefaults.buttonColors(
                backgroundColor = Color.Blue,
                contentColor = Color.White)
        ) {
            Text("Next screen",
                fontSize = 30.sp)
        }
    }
}