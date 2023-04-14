package com.loncar.composeapp.view.main

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.CircularProgressIndicator
import androidx.compose.material.MaterialTheme
import androidx.compose.material.OutlinedTextField
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import com.loncar.composeapp.R
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.view.common.getCity
import com.loncar.composeapp.view.common.hashtags
import com.loncar.composeapp.viewmodel.PicturesState
import com.loncar.composeapp.viewmodel.SearchState

@Composable
fun HomeScreen(
    picturesState: PicturesState,
    currentUserHandle: String?,
    onItemClick: (id: Int) -> Unit,
    onSearch: () -> Unit,
    searchState: SearchState,
    onInputChanged: (input: String) -> Unit
) {
    if (picturesState.loading) {
        Box(
            modifier = Modifier.fillMaxSize(),
            contentAlignment = Alignment.Center
        ) {
            CircularProgressIndicator()
        }
    } else {
        var nonUserPictures = picturesState.pictures.filter { it.handle != currentUserHandle }
        val filter = searchState.input

        if (filter != "" && filter != "@" && filter != "#" && filter != "~") {
            if (filter[0] == '@') {
                nonUserPictures = nonUserPictures.filter { it.handle == filter.drop(1) }
            } else if (filter[0] == '#') {
                nonUserPictures = nonUserPictures.filter { filter.drop(1) in hashtags(it) }
            } else if (filter[0] == '~') {
                nonUserPictures = nonUserPictures.filter {
                    getCity(
                        LocalContext.current,
                        it.lat.toDouble(),
                        it.lng.toDouble()
                    ) == filter.drop(1)
                }
            }
        }

        Column() {
            OutlinedTextField(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(15.dp),
                value = searchState.input,
                onValueChange = onInputChanged,
                label = {
                    Text(
                        text = stringResource(id = R.string.search),
                        style = MaterialTheme.typography.body1
                    )
                },
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Text,
                    imeAction = ImeAction.Search
                ),
                keyboardActions = KeyboardActions(
                    onSearch = { onSearch() }
                )
            )

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
                    nonUserPictures.forEach {
                        item {
                            AsyncImage(
                                model = it.resource,
                                contentDescription = "image",
                                contentScale = ContentScale.Crop,
                                placeholder = painterResource(id = R.drawable.placeholder),
                                modifier = Modifier
                                    .padding(8.dp)
                                    .fillMaxSize()
                                    .aspectRatio(1f)
                                    .clip(RoundedCornerShape(10.dp))
                                    .clickable { onItemClick(it.id.toInt()) }
                            )
                        }
                    }
                })
        }
    }
}

