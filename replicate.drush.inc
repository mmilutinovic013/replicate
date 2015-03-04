<?php
/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {
  $items = array();
  $items['replicate-drush-entity-by-id'] = array(
    'description' => 'Replicate an Enitity via Drush!',
    'arguments' => array(
      'entity-type' => dt('Type of Entity (eg. Node) that you wish to replicate'),
      'id-number' => dt('ID value of the specified Entity Type (eg. NodeID'),

    ),
    'aliases' => array('rep', 'replicate'),
    'examples' => array(
      'drush replicate node 1' =>
        'Node 1 is replicated via drush using full command',
      'drush rep node 1' =>
        'Node 1 is replicated via drush using aliased command',
    ),
  );

  return $items;
}
/**
 * Implements hook_drush_help().
 */
function replicate_drush_help($command) {
  switch ($command) {
    case 'drush:replicate-drush-entity-by-id':
      return dt('This allows a user to replicate an entity by providing an entity type and id.');
  }
}
/**
 * Implements replicate_entity_by_id().
 */
function drush_replicate_drush_entity_by_id($entity_type = NULL, $id = NULL) {
  if (!is_null($entity_type) && !is_null($id) ){
    $entity_id = replicate_entity_by_id($entity_type, $id);
    if (isset($entity_id)) {
      $returnvalue = "Congratulations your cloned " . $entity_type . " is " . $entity_type . " " . $entity_id;
      return drush_print($returnvalue);
    }
  }
  return "Missing Arguments! Please enter a valid entity type and number!";
}
