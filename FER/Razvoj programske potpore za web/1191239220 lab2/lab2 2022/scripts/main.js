function refreshCartItems(){
	// INSERT CODE HERE --> PRIPREMA

	let lslength = 0;
	for(let i=0; i<localStorage.length; ++i)
		lslength += Number(localStorage.getItem(localStorage.key(i)));

	document.getElementById('cart-items').textContent = String(lslength);
	
	// END INSERT --> PRIPREMA
}

refreshCartItems();