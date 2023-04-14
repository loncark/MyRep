package com.loncar.composeapp

import androidx.compose.ui.test.assertIsDisplayed
import androidx.compose.ui.test.junit4.ComposeContentTestRule
import androidx.compose.ui.test.junit4.createComposeRule
import androidx.compose.ui.test.onNodeWithTag
import androidx.compose.ui.test.onNodeWithText
import androidx.compose.ui.test.performClick
import com.loncar.composeapp.model.Person
import com.loncar.composeapp.model.dummyPictures
import com.loncar.composeapp.ui.theme.ComposeAppTheme
import com.loncar.composeapp.view.main.UserScreen
import com.loncar.composeapp.viewmodel.PersonsState
import com.loncar.composeapp.viewmodel.PicturesState
import org.junit.Rule
import org.junit.Test

class UserScreenTest {

    @get:Rule
    val testRule: ComposeContentTestRule = createComposeRule()

    @Test
    fun anonymousStateIsRendered() {
        testRule.setContent {
            ComposeAppTheme {
                UserScreen(handle = null,
                    personsState = PersonsState(emptyList(), null, false),
                    picturesState = PicturesState(emptyList(), false),
                    onItemClick = {},
                    onLogOut = {},
                )
            }
        }

        testRule.onNodeWithText("You are in anonymous mode.").assertIsDisplayed()
    }

    @Test
    fun logOutButtonIsDisplayed_PictureClickNavigation() {
        val dummyPerson = Person("red@gmail.com","red", "https://firebasestorage.googleapis.com/v0/b/composeapp-47d09.appspot.com/o/pictures%2Fred%2Fred2.jpg?alt=media&token=343b6997-e1f5-44c3-9a15-13a9ae4ed6de", "Morbi non ullamcorper odio, nec sagittis nibh. In in est cursus, tincidunt felis vel, efficitur lorem. Cras maximus odio ut ante ultrices ultrices.")

        testRule.setContent {
            ComposeAppTheme {
                UserScreen(handle = "red",
                    personsState = PersonsState(listOf(dummyPerson), "red", false),
                    picturesState = PicturesState(dummyPictures, false),
                    onItemClick = {
                        assert(it.toString() == dummyPictures[0].id)
                    },
                    onLogOut = {},
                )
            }
        }

        testRule.onNodeWithText("Log out").assertIsDisplayed()
        testRule.onNodeWithTag("image26").performClick()
    }
}