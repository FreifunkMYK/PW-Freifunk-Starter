<?php
$routers = $page->children("template=router");
$output = '';

foreach($routers as $router){
  $title = $router->title;
  $image = (count($router->image) ? $router->image->first()->size(300,300)->url : 'https://placehold.it/300x300');
  $features = getTag($router->features, 2);

  $output .= "<a href='{$router->httpUrl}'>
                <article id='article-{$router->id}' class='large-3 small-6 columns'>
                  <img class='img-responsive panel-thumbnail' src='$image'></img>
                  <div class='panel'>
                    <h5>$title</h5>
                    <ul class='inline-list'>
                      $features
                    </ul>
                  </div>
                </article><!-- #article-7 -->
              </a>";

}

$sidebar = renderSidebarFilter();

$content = "<div id='article' class='large-10 columns'>
              <div class='row'>
                $output
              </div><!--# row -->
            </div><!-- #article -->
            $sidebar";
