package com.loncar.composeapp.view.main

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.semantics.contentDescription
import androidx.compose.ui.semantics.semantics
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import com.loncar.composeapp.R
import com.loncar.composeapp.viewmodel.PersonsState
import com.loncar.composeapp.viewmodel.PicturesState

@Composable
fun UserScreen(
    handle: String?,
    personsState: PersonsState,
    picturesState: PicturesState,
    onItemClick: (id:Int) -> Unit,
    onLogOut: () -> Unit
) {
    if (picturesState.loading) {
        Box(
            modifier = Modifier.fillMaxSize(),
            contentAlignment = Alignment.Center
        ) {
            CircularProgressIndicator()
        }
    } else {
        val person = personsState.persons.find { it.handle == handle }

        if (person == null) {
            Column(
                verticalArrangement = Arrangement.Center,
                horizontalAlignment = Alignment.CenterHorizontally
            ) {
                Text(text = "You are in anonymous mode.")
            }
        } else {
            val pictures = picturesState.pictures.filter { it.handle == person.handle }

            Scaffold(
                content = {
                    Column() {
                        Row(
                            horizontalArrangement = Arrangement.SpaceEvenly,
                            verticalAlignment = Alignment.CenterVertically,
                            modifier = Modifier
                                .fillMaxWidth()
                        ) {
                            AsyncImage(
                                model = person.icon,
                                contentDescription = "image",
                                contentScale = ContentScale.Crop,
                                modifier = Modifier
                                    .padding(top = 15.dp)
                                    .clip(RoundedCornerShape(10.dp))
                                    .size(100.dp)
                                    .aspectRatio(1f)
                            )

                            Column(
                                horizontalAlignment = Alignment.CenterHorizontally,
                                verticalArrangement = Arrangement.SpaceEvenly,
                                modifier = Modifier.padding(10.dp)
                            ) {
                                Text(
                                    text = "@" + person.handle,
                                    modifier = Modifier.padding(5.dp),
                                    style = MaterialTheme.typography.h1
                                )
                                if (handle == personsState.currentUserHandle) {
                                    Button(
                                        onClick = onLogOut,
                                    ) {
                                        Text("Log out")
                                    }
                                }
                            }
                        }

                        Row(
                            horizontalArrangement = Arrangement.SpaceEvenly,
                            verticalAlignment = Alignment.CenterVertically,
                            modifier = Modifier
                                .padding(15.dp)
                                .fillMaxWidth()
                        ) {
                            Text(
                                text = person.bio,
                                style = MaterialTheme.typography.body1
                            )
                        }

                        LazyVerticalGrid(
                            columns = GridCells.Fixed(2),
                            modifier = Modifier.fillMaxSize(),
                            contentPadding = PaddingValues(
                                start = 5.dp,
                                top = 5.dp,
                                end = 5.dp,
                                bottom = 5.dp
                            ),
                            content = {
                                pictures.forEach {
                                    item {
                                        AsyncImage(
                                            model = it.resource,
                                            contentDescription = "image" + it.id,
                                            contentScale = ContentScale.Crop,
                                            placeholder = painterResource(id = R.drawable.placeholder),
                                            modifier = Modifier
                                                .padding(5.dp)
                                                .fillMaxSize()
                                                .aspectRatio(1f)
                                                .clip(RoundedCornerShape(10.dp))
                                                .clickable { onItemClick(it.id.toInt()) }
                                                .testTag("image" + it.id)
                                        )
                                    }
                                }
                            }
                        )
                    }
                }
            )
        }
    }
}
