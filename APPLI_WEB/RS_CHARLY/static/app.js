/** Stop tank */
function stopTank(){
    console.log("Stop tank !");
    $.ajax({
      url: "/stop_tank",
      method: "GET"
    })
}

/** Stop arm */
function stopArm(){
  console.log("Stop arm !");
  $.ajax({
    url: "/stop_arm",
    method: "GET"
  })
}