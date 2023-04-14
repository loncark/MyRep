package com.loncar.composeapp

import androidx.compose.ui.test.*
import androidx.compose.ui.test.junit4.ComposeContentTestRule
import androidx.compose.ui.test.junit4.createComposeRule
import com.loncar.composeapp.ui.theme.ComposeAppTheme
import com.loncar.composeapp.view.main.UploadScreen
import com.loncar.composeapp.viewmodel.Filter
import com.loncar.composeapp.viewmodel.UploadState
import junit.framework.Assert.assertEquals
import kotlinx.coroutines.runBlocking
import okhttp3.internal.wait
import org.junit.Rule
import org.junit.Test

class UploadScreenTest {

    @get:Rule
    val testRule: ComposeContentTestRule = createComposeRule()

    @Test
    fun noPictureLoaded() {
        var state = UploadState("", "", null, false, 0, null, Filter.NONE)

        testRule.setContent {
            ComposeAppTheme {
                UploadScreen(
                    uploadState = state,
                    currentUserHandle = "red",
                    onDescriptionChanged = { new ->
                        state = state.copy(   // fetch using value
                            description = new
                        ) },
                    onHashtagsChanged = {},
                    onUriChanged = {},
                    onUpload = {},
                    onUpdate = {},
                    onCancel = {},
                    onFilterChanged = {}
                )
            }
        }

        testRule.onNodeWithText("No image selected.").assertIsDisplayed()

        testRule.onNodeWithTag("textField").performTextInput("New description.")
        assertEquals(state.description, "New description.")
    }

    @Test
    fun pictureUpdate() {

        var selectedFilter: Filter? = Filter.NONE

        testRule.setContent {
            ComposeAppTheme {
                UploadScreen(
                    uploadState = UploadState("", "", null, true, 0, "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fblue%2Fblue2.jpg?alt=media&token=42236c82-d174-4542-9a09-146dab7c34fb", Filter.NONE),
                    currentUserHandle = "blue",
                    onDescriptionChanged = {},
                    onHashtagsChanged = {},
                    onUriChanged = {},
                    onUpload = {},
                    onUpdate = {},
                    onCancel = {},
                    onFilterChanged = {filter ->
                        selectedFilter = filter
                    }
                )
            }
        }

        testRule.onNodeWithText("Cancel").assertIsDisplayed()
        testRule.onNodeWithText("No image selected.").assertDoesNotExist()
        testRule.onNodeWithTag("updateImage").assertExists()
    }
}