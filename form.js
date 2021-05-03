var currentTab = 0;
showTab(currentTab);

function showTab(currentTabi){
    var tab = document.getElementsByClassName("tab");
    tab[currentTabi].style.display = "block";

    if(currentTab == 0){
        document.getElementById("prevBtn").style.display = "none";
    } else {
        document.getElementById("prevBtn").style.display = "inline";
    }

    if(currentTab == (tab.length -1)){
        console.log("top if");
        document.getElementById("nextBtn").style.display = "none";
        document.getElementById("submitBtn").style.display ="inline";
    } else {
        console.log("bottom if");
        document.getElementById("nextBtn").style.display = "inline";
        document.getElementById("submitBtn").style.display ="none";
    }
    fixStepIndicator(currentTabi);
}

function nextPrev(currentTabi){
    var tab = document.getElementsByClassName("tab");

    tab[currentTab].style.display = "none";

    currentTab = currentTab + currentTabi;

    if(currentTab >= tab.length){
        return false;
    }
    showTab(currentTab);
}

function fixStepIndicator(n) {
    var x = document.getElementsByClassName("step");

    for (i = 0; i < x.length; i++) {
        x[i].className = x[i].className.replace(" active", "");
    }
    x[n].className += " active";
}