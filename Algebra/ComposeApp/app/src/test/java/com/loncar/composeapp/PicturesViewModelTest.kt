package com.loncar.composeapp

import androidx.compose.runtime.mutableStateOf
import com.loncar.composeapp.api.PicturesApi
import com.loncar.composeapp.model.Picture
import com.loncar.composeapp.model.dummyPictures
import com.loncar.composeapp.repository.PicturesRepository
import com.loncar.composeapp.room.PictureDao
import com.loncar.composeapp.viewmodel.PicturesState
import com.loncar.composeapp.viewmodel.PicturesViewModel
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.delay
import kotlinx.coroutines.test.StandardTestDispatcher
import kotlinx.coroutines.test.TestScope
import kotlinx.coroutines.test.advanceUntilIdle
import kotlinx.coroutines.test.runTest
import org.junit.Test

@ExperimentalCoroutinesApi
class PicturesViewModelTest {
    private val dispatcher = StandardTestDispatcher()
    private val scope = TestScope(dispatcher)

    private fun getViewModel() : PicturesViewModel {
        val fakePicturesState = mutableStateOf(PicturesState(emptyList(), true))
        val fakeRepository = PicturesRepository(FakeApi(), FakePictureDao(), dispatcher)

        return PicturesViewModel(fakeRepository, fakePicturesState, dispatcher)
    }

    @Test
    fun initialStateIsProduced() = scope.runTest {
        val fakePicturesViewModel = getViewModel()
        val initialState = fakePicturesViewModel.picturesState.value
        assert(initialState == PicturesState(emptyList(), true))
    }

    @Test
    fun stateWithContentIsProduced() = scope.runTest {
        val testVM = getViewModel()
        advanceUntilIdle()  //try  waitForIdle()
        val state = testVM.picturesState.value

        assert(state == PicturesState(dummyPictures, false))
    }
}

class FakeApi : PicturesApi {
    override suspend fun getPictures(): Map<String, Picture> {
        val keysList = listOf("1", "2", "3", "4", "5", "6", "7", "8")
        val map: Map<String, Picture> = keysList.zip(dummyPictures).toMap()
        delay(1000)
        return map
    }
}

class FakePictureDao : PictureDao {
    override suspend fun getAllPictures() : List<Picture> {
        delay(1000)
        return dummyPictures        // throws an exception?
    }
    override suspend fun addAll(pictures: List<Picture>) {}
    override suspend fun insertPicture(picture: Picture) {}
    override suspend fun update(picture: Picture) {}

}