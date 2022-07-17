function addToCart(id) {
	// INSERT CODE HERE --> PRIPREMA

	if(localStorage.getItem(id)==null)
		localStorage.setItem(id, 1);
	else {
			let temp = localStorage.getItem(id);
			localStorage.removeItem(id);
			localStorage.setItem(id, Number(temp)+1);
	}

	refreshCartItems();
	// END INSERT --> PRIPREMA
}

let getData = async function () {
	let response = await fetch("https://web1lab2.azurewebsites.net/categories");
	let data = await response.json();
	addCategories(data);
	
}

let addCategories = async function (categories) {
	let main = document.querySelector('main');
	let categoryTemplate = document.querySelector('#category-template');

	for (let index = 0; index < categories.length; index++) {
		// prepisuje cijeli category-template element u category
		let category = categoryTemplate.content.cloneNode(true);
		let categoryTitleElement = category.querySelector('.decorated-title > span');
		categoryTitleElement.textContent = categories[index].name;
		
		let productsResponse = await fetch("https://web1lab2.azurewebsites.net/products?categoryId=" + categories[index].id);
		let products = await productsResponse.json();

		// INSERT CODE HERE --> PRIPREMA

		// 1. ubaciti u gallery svakog category-ja niz products po istom kljucu kao gore
		// 2. implementirati funkcionalnost onclick->addToCart 

		let productTemplate = document.querySelector('#product-template');
		
		for(let i=0; i<products.length; ++i){

			let product = productTemplate.content.cloneNode(true);
			let productTitleElement = product.querySelector('.photo-box-title');
			let productImageElement = product.querySelector('.photo-box-image');
			
			productTitleElement.textContent = products[i].name;
			productImageElement.src = products[i].imageUrl;

			let productCartButton = product.querySelector('.cart-btn');
			productCartButton.onclick = () => addToCart(products[i].name);
			
			category.querySelector('.gallery').appendChild(product);
		}

		// END INSERT --> PRIPREMA

		main.appendChild(category);
	}
};
getData();