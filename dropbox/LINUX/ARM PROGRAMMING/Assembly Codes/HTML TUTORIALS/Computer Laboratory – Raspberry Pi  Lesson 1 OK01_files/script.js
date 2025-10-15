function ExpandToggle(topicID) {
    var expand = document.getElementById(topicID);
    if (expand.style.display == "block") {
        expand.style.display = "none"
    } else {
        expand.style.display = "block"
    }
    return true;
}
