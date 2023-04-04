package com.loncar.composeapp.view.main

import android.widget.Toast
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.CircularProgressIndicator
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.LocationOn
import androidx.compose.material.icons.filled.Update
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.SpanStyle
import androidx.compose.ui.text.buildAnnotatedString
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.withStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import coil.compose.AsyncImage
import com.loncar.composeapp.R
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.ui.theme.fonts
import com.loncar.composeapp.view.common.downloadImage
import com.loncar.composeapp.view.common.getCity
import com.loncar.composeapp.view.common.hashtags
import me.saket.swipe.SwipeAction
import me.saket.swipe.SwipeableActionsBox

@Composable
fun PictureScreen(
    picture: Picture,//?,
    currentUserHandle: String?,
    onPersonClick: (handle: String) -> Unit,
    onLocationClick: (id: Int) -> Unit,
    onDelete: (id: Int, url: String) -> Unit,
    onUpdate: (id: Int, pictureToUpdateResource: String) -> Unit
) {
    val context = LocalContext.current
    val updateAction = SwipeAction(
        icon = {
            Icon(
                modifier = Modifier.size(150.dp),
                imageVector = Icons.Default.Update,
                contentDescription = stringResource(R.string.update),
                tint = Color.Green
            )
        },
        background = Color.LightGray,
        onSwipe = { onUpdate(picture.id.toInt(), picture.resource) }
    )
    val deleteAction = SwipeAction(
        icon = {
            Icon(
                modifier = Modifier.size(150.dp),
                imageVector = Icons.Default.Delete,
                contentDescription = stringResource(R.string.delete),
                tint = Color.Red
            )
        },
        background = Color.LightGray,
        onSwipe = { onDelete(picture.id.toInt(), picture.resource) }
    )

    Column(
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally,
        modifier = Modifier
            .padding(15.dp)
            .verticalScroll(rememberScrollState())
    ) {
        if (currentUserHandle == picture.handle) {
            SwipeableActionsBox(            // DON'T SWIPE IT TOO FAR OR IT WILL CRASH
                startActions = listOf(updateAction),
                endActions = listOf(deleteAction),
                modifier = Modifier
                    .clip(RoundedCornerShape(10.dp))
                    .background(MaterialTheme.colors.background)
            ) {
                AsyncImage(
                    model = picture.resource,
                    contentDescription = "pic",
                    modifier = Modifier
                        .fillMaxWidth()
                        .clip(RoundedCornerShape(10.dp))
                        .clickable {
                            Toast
                                .makeText(
                                    context,
                                    context.getString(R.string.downloading_picture),
                                    Toast.LENGTH_LONG
                                )
                                .show()
                            downloadImage(picture.resource, context)
                        }
                )
            }
        } else {
            AsyncImage(
                model = picture.resource,
                contentDescription = "pic",
                modifier = Modifier
                    .fillMaxWidth()
                    .clip(RoundedCornerShape(10.dp))
                    .clickable {
                        Toast
                            .makeText(
                                context,
                                context.getString(R.string.downloading_picture),
                                Toast.LENGTH_LONG
                            )
                            .show()
                        downloadImage(picture.resource, context)
                    }
            )
        }

        Text(
            buildAnnotatedString {
                withStyle(
                    style = SpanStyle(
                        fontSize = 15.sp,
                        fontWeight = FontWeight.Bold,
                        fontFamily = fonts
                    )
                ) {
                    append("@${picture.handle} ")
                }
                append("writes:")
            },
            modifier = Modifier
                .padding(top = 10.dp, bottom = 10.dp)
                .clickable { onPersonClick(picture.handle) }
        )

        Text(picture.description, style = MaterialTheme.typography.body1)

        Row(
            horizontalArrangement = Arrangement.Center,
            verticalAlignment = Alignment.CenterVertically,
            modifier = Modifier.padding(10.dp)
        ) {
            Icon(Icons.Default.LocationOn, contentDescription = "icon")

            val location =
                getCity(LocalContext.current, picture.lat.toDouble(), picture.lng.toDouble())
            Text(
                text = location,
                style = MaterialTheme.typography.body1,
                modifier = Modifier
                    .padding(5.dp)
                    .clickable {
                        onLocationClick(picture.id.toInt())
                    }
            )
        }

        var tags = ""
        val hashtags = hashtags(picture)
        if (hashtags.isNotEmpty()) {
            hashtags.forEach {
                tags += "#$it "
            }
            Text(tags)
        }
    }
}