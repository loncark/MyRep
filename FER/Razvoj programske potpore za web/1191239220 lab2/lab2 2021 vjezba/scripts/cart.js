let lslength = 0;
for(let i=0; i<localStorage.length; ++i)
	lslength += Number(localStorage.getItem(localStorage.key(i)));

document.getElementById('cart-items').textContent = String(lslength);

let getData = async function () {
	let productsResponse = await fetch("https://web1lab2.azurewebsites.net/products");
	let products = await productsResponse.json();
	addproducts(products);
	
}

let addproducts = async function (productsOriginal) {
	let cart = document.querySelector('.cart');
	let section = cart.parentNode;

	//Filter
	let cartTemplateFilter = document.querySelector('#filter');

	let apply = cartTemplateFilter.content.querySelector('.cart-filter-apply');
	let clear = cartTemplateFilter.content.querySelector('.cart-filter-clear');
	let field = cartTemplateFilter.content.querySelector('.cart-filter-text');

	let products = productsOriginal;

	clear.onclick = () => {
		field.value = field.defaultValue; 
		products = productsOriginal;
	}
console.log("original: ", products);
	apply.onclick = () => {//trazi u polju adekvatne itemove
		
		let unos = field.value; //string, cak i kad je broj

		if(isNaN(unos)==false && unos!="") {
			for(let i=0; i<products.length; ++i){
				if(products[i].price!=Number(unos) && 
				localStorage.getItem(products[i].name)!=unos)
					products.splice(i,1);
			}
			console.log("broj: ", products);
		}
		else if(unos!="") 
			{	console.log(unos);
				for(let i=0; i<products.length; ++i){
					if(products[i].name.includes(unos)==false)
						products.splice(i,1);
				}
				console.log("rijec: ", products);
				
			}
	}

	/* NE ZNAM USTIMAT PROMJENU LISTE 
	VJV TREBA U IF-ELSEU IZNAD REMOVAT 
	ELEMENTE KOJI SU DODANI KODOM NIZE I
	DODAT NOVE S IZMIJENJENM PRODUCTS NIZOM*/

	section.insertBefore(cartTemplateFilter.content, cart);

	//Naslov i popis
	let cartTemplateHeader = document.querySelector('#cart-template-header');
	cart.appendChild(cartTemplateHeader.content);

	//ZA SVAKI ITEM: CART.APPENDCHILD()
	let cartTemplateItem = document.querySelector('#cart-template-item');

	for (let index = 0; index < products.length; index++) {
		// prepisuje cijeli cartTemplateItem element u item
		let item = cartTemplateItem.content.cloneNode(true);
		
		let itemTitleElement = item.querySelector('.cart-item-title');
		itemTitleElement.textContent = products[index].name;

		let itemPriceElement = item.querySelector('.cart-item-price');
		itemPriceElement.textContent = products[index].price + " kn";

		let itemQuantityElement = item.querySelector('.cart-item-quantity');
		itemQuantityElement.textContent = 
		Number(localStorage.getItem(products[index].name));
		
		cart.appendChild(item);

	}
};
getData();