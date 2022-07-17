function getCart() {
    //INSERT CODE HERE - Zadatak
    let map = new Map();

    for(let i=0; i<localStorage.length; ++i)
    {
        let id = localStorage.key(i); 
        if(isNaN(id)) continue;
        map.set(id, localStorage.getItem(id));
    }

    console.log(map);

    return map;
   //END INSERT CODE - Zadatak
}

 let refreshCart = async function () {
    let map = getCart();
    if(map){
        if(map.size < 1) return;
        let container = document.querySelector('.cart');
		container.innerHTML = "";
        
        let cartHeaderTemplate = document.querySelector('#cart-template-header');
        let cartHeader = cartHeaderTemplate.content.cloneNode(true);
        container.appendChild(cartHeader);

        //INSERT CODE HERE - Zadatak
		 
        let response = await fetch("scripts/lab2.json");

        let promo = document.querySelector('#promo-code-text');
        let button = document.querySelector('#promo-code-button');
        let status = document.querySelector('#promo-code-status');
        let priceChanged = document.querySelector('.cart-item-price');

        //NE ZNAM PROMIJENITI CIJENU KAD SE UKUCA KOD I KLIKNE SUBMIT
        button.onclick = () => {  
                if (promo.value=="WEBLAB2") {
                    if(localStorage.getItem("popust")) localStorage.removeItem("popust");
                    localStorage.setItem("popust", 1);
                    status.textContent = "20% Discount applied. Enjoy!";
                    promo.value = "";
                    priceChanged *= 0.8;
                } 
                else {
                    if(localStorage.getItem("popust")) localStorage.removeItem("popust");
                    localStorage.setItem("popust", 0); 
                    status.textContent = "Discount not applied.";
                    promo.value = "";
                    priceChanged *= 1.2;
                }
            
        }

        //END INSERT CODE - Zadatak
        let data = await response.json();
        
        let cartItemTemplate = document.querySelector('#cart-template-item');
        for(const id of map.keys()){
            let product = data.products.find(p => p.id == id);
            let cartItem = cartItemTemplate.content.cloneNode(true);
            
            cartItem.querySelector(".cart-item").dataset.id = id;
            let title = cartItem.querySelector('.cart-item-title');
            title.textContent = product.name;
            let quantity = cartItem.querySelector('.cart-item-quantity');
            quantity.value = map.get(id);
                
            //INSERT CODE HERE - Zadatak
            
            let discount = localStorage.getItem("popust");
            let price = cartItem.querySelector('.cart-item-price');
            
            price.textContent = product.price;

            //END INSERT CODE - Zadatak

            container.appendChild(cartItem);
        }
    }
}

refreshCart();