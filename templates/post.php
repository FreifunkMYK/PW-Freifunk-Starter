<?php

$image = (count($page->images) ? $page->images->first()->size(300,200)->url : "https://placehold.it/200x130");

$output = "<article id='article-{$page->id}' class='row article'>
              <div class='medium-3 columns'>
                <img class='responsive' src='$image'></img>
              </div>
              <div class='medium-9 columns'>
                <h4 class='tobheader'><small>{$page->date}</small></h4>
                <a href='{$page->httpUrl}'><h3>{$page->title}</h3></a>
                <p>
                    {$page->get('body|summary')}
                </p>
              </div>
          </article><!-- #article-7 -->";

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
