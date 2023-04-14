package com.loncar.composeapp.view.main

import android.net.Uri
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.selection.selectable
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.focus.FocusDirection
import androidx.compose.ui.graphics.ColorMatrix
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.platform.testTag
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import com.bumptech.glide.integration.compose.ExperimentalGlideComposeApi
import com.bumptech.glide.integration.compose.GlideImage
import com.loncar.composeapp.R
import com.loncar.composeapp.viewmodel.Filter
import com.loncar.composeapp.viewmodel.UploadState
import com.loncar.composeapp.viewmodel.sepiaMatrix
import androidx.compose.ui.graphics.ColorFilter.Companion as ColorFilterAlias

@OptIn(ExperimentalGlideComposeApi::class)
@Composable
fun UploadScreen(
    uploadState: UploadState,
    currentUserHandle: String?,
    onDescriptionChanged: (description: String) -> Unit,
    onHashtagsChanged: (hashtags: String) -> Unit,
    onUriChanged: (uri: Uri?) -> Unit,
    onUpload: () -> Unit,
    onUpdate: () -> Unit,
    onCancel: () -> Unit,
    onFilterChanged: (filter: Filter) -> Unit
) {
    val focusManager = LocalFocusManager.current

    if (currentUserHandle == null) {
        Column(
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text("You are in anonymous mode.")
        }
    } else {

        Column(
            verticalArrangement = Arrangement.Center,
            modifier = Modifier
                .padding(15.dp)
                .verticalScroll(rememberScrollState())
        ) {
            OutlinedTextField(
                modifier = Modifier
                    .fillMaxWidth()
                    .testTag("textField"),
                value = uploadState.description,
                onValueChange = onDescriptionChanged,
                label = {
                    Text(
                        text = stringResource(id = R.string.description),
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

            OutlinedTextField(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 10.dp),
                value = uploadState.hashtags,
                onValueChange = onHashtagsChanged,
                label = {
                    Text(
                        text = stringResource(id = R.string.hashtags),
                        style = MaterialTheme.typography.body1
                    )
                },
                keyboardOptions = KeyboardOptions(
                    keyboardType = KeyboardType.Text,
                    imeAction = ImeAction.Done
                )
            )

            if (uploadState.isUpdate) {
                Row(
                    horizontalArrangement = Arrangement.SpaceBetween,
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Button(
                        onClick = onUpdate,
                        modifier = Modifier.padding(vertical = 15.dp)
                    ) {
                        Text("Update")
                    }

                    Button(
                        onClick = onCancel,
                        modifier = Modifier.padding(vertical = 15.dp)
                    ) {
                        Text("Cancel")
                    }
                }

                AsyncImage(
                    model = uploadState.pictureToUpdateResource,
                    contentDescription = "pic",
                    modifier = Modifier
                        .fillMaxWidth()
                        .clip(RoundedCornerShape(10.dp))
                        .testTag("updateImage")
                )

            } else {
                val galleryLauncher =
                    rememberLauncherForActivityResult(
                        ActivityResultContracts.GetContent(),
                        onResult = onUriChanged
                    )

                Row(
                    horizontalArrangement = Arrangement.SpaceBetween,
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Button(
                        onClick = { galleryLauncher.launch("image/*") },
                        modifier = Modifier.padding(vertical = 15.dp)
                    ) {
                        Text("Browse Gallery")
                    }

                    Button(
                        onClick = onUpload,
                        modifier = Modifier.padding(vertical = 15.dp)
                    ) {
                        Text("Upload")
                    }
                }

                if (uploadState.uri != null) {

                    val colorMatrix = ColorMatrix().apply {
                        if(uploadState.filter == Filter.GRAYSCALE) { setToSaturation(0f) }
                        else if(uploadState.filter == Filter.SEPIA) { set(ColorMatrix(sepiaMatrix)) }
                    }

                    val colorFilter = ColorFilterAlias.colorMatrix(colorMatrix)

                    GlideImage(
                        model = uploadState.uri,
                        contentDescription = "Selected image",
                        modifier = Modifier
                            .clip(RoundedCornerShape(10.dp))
                            .fillMaxSize(),
                        colorFilter = colorFilter
                    )

                    FilterRadioButtons(onFilterChanged)

                } else {
                    Text(
                        text = "No image selected.",
                        style = MaterialTheme.typography.body1,
                        textAlign = TextAlign.Center,
                        modifier = Modifier
                            .padding(10.dp)
                            .align(Alignment.CenterHorizontally)
                    )
                }
            }
        }
    }
}

@Composable
fun FilterRadioButtons(onFilterChanged: (filter: Filter) -> Unit) {
    val radioOptions = listOf(Filter.GRAYSCALE, Filter.SEPIA, Filter.NONE)
    val (selectedOption, onOptionSelected) = remember { mutableStateOf(radioOptions[2]) }
    Column(
        Modifier.padding(top = 15.dp)
    ) {
        radioOptions.forEach { text ->
            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .selectable(
                        selected = (text == selectedOption),
                        onClick = {
                            onOptionSelected(text)
                            onFilterChanged(text)
                        }
                    ),
                verticalAlignment = Alignment.CenterVertically
            ) {
                RadioButton(
                    selected = (text == selectedOption),
                    onClick = {
                        onOptionSelected(text)
                        onFilterChanged(text)
                    }
                )
                Text(
                    text = text.toString().lowercase().replaceFirstChar { it.uppercase() },
                    style = MaterialTheme.typography.body1,
                )
            }
        }
    }
}
