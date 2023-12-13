/** Stop tank */
function stopMouvement(){
    console.log("Stop mouvement !");
    $.ajax({
      url: "/stop_tank",
      method: "GET"
    })
}