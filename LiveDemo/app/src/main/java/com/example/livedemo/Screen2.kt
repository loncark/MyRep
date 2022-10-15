package com.example.livedemo

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp

    @Composable
    fun Screen2() {

        LazyColumn(verticalArrangement = Arrangement.SpaceEvenly,
            horizontalAlignment = Alignment.CenterHorizontally,
            modifier = Modifier.fillMaxWidth()) {

            val resourceList = listOf(R.drawable.image, R.drawable.image2, R.drawable.image3, R.drawable.image4)

            items(resourceList) {
                Image(
                    painter = painterResource(it),
                    contentDescription = "an image",
                    modifier = Modifier.padding(10.dp).fillParentMaxSize()
                )
            }

        }
    }
