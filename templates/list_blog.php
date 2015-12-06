<?php

$output = '';

$posts = $pages->find("template=post,sort=-date");

foreach($posts as $post){
  $image = (count($post->images) ? $post->images->first()->size(300,200)->url : "https://placehold.it/200x130");

  $output .= "<article id='article-{$post->id}' class='row article'>
                <div class='medium-3 columns'>
                  <img class='responsive' src='$image'></img>
                </div>
                <div class='medium-9 columns'>
                  <h4 class='tobheader'><small>{$post->date}</small></h4>
                  <a href='{$post->httpUrl}'><h3>{$post->title}</h3></a>
                  <p>
                      {$post->get('body|summary')}
                  </p>
                </div>
            </article><!-- #article-7 -->
            <hr>";
};

$content = "<div id='article' class='blog-list large-9 columns'>
              $output
            </div><!-- #article -->
            <div id='sidebar' class='large-3 columns'>
              <div class='panel'>
                <h5>Mitmachen</h5>
                <p>
                  Unterstütze Freifunk und stelle deinen eigenen Freifunk-Router auf um das Netz zu erweitern.
                </p>
                <a href='#' class='button expand'>Informier dich jetzt!</a>
              </div>
              <h5>Neueste Router</h5>
              <ul>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
                <li>Koblenz, Marktplatz</li>
              </ul>
            </div>";
