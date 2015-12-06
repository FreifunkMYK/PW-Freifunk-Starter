<?php

if($input->urlSegment3) throw new Wire404Exception();

$username = $users->get($input->urlSegment1);

if($username instanceof NullPage) throw new Wire404Exception();
